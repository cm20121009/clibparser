//
// Project: clibparser
// Created by bajdcc
//

#ifndef CLIBPARSER_CVFS_H
#define CLIBPARSER_CVFS_H

#include <vector>
#include <map>
#include <memory>
#include "memory.h"

namespace clib {

    // 权限
    struct vfs_mod {
        char rwx[3];
    };

    enum vfs_file_t {
        fs_file,
        fs_dir,
        fs_func,
    };

    class vfs_func_t {
    public:
        virtual string_t callback(const string_t &path) = 0;
    };

    // 结点
    struct vfs_node {
        using ref = std::shared_ptr<vfs_node>;
        using weak_ref = std::weak_ptr<vfs_node>;
        vfs_file_t type;
        vfs_mod mod[3];
        int owner;
        struct {
            time_t create;
            time_t access;
            time_t modify;
        } time;
        int refs;
        bool locked;
        string_t name;
        std::map<string_t, ref> children;
        std::vector<byte> data;
        vfs_func_t *callback;
        weak_ref parent;
    };

    struct vfs_user {
        int id;
        string_t name;
        string_t password;
    };

    class vfs_node_dec {
    public:
        virtual bool available() const = 0;
        virtual int index() const = 0;
        virtual void advance();
        virtual ~vfs_node_dec() = default;
    protected:
        int idx{0};
    };

    class cvfs;
    class vfs_node_solid : public vfs_node_dec {
        friend class cvfs;
    public:
        ~vfs_node_solid() override;
        bool available() const override;
        int index() const override;
    private:
        explicit vfs_node_solid(const vfs_node::ref &ref);
        vfs_node::weak_ref node;
    };

    class vfs_node_cached : public vfs_node_dec {
        friend class cvfs;
    public:
        bool available() const override;
        int index() const override;
    private:
        explicit vfs_node_cached(const string_t &str);
        string_t cache;
    };

    class cvfs {
    public:
        cvfs();

        void reset();
        string_t get_user() const;
        string_t get_pwd() const;
        int get(const string_t &path, vfs_node_dec **dec = nullptr, vfs_func_t *f = nullptr) const;
        bool read_vfs(const string_t &path, std::vector<byte> &data) const;
        bool write_vfs(const string_t &path, const std::vector<byte> &data);

        void as_root(bool flag);

        int cd(const string_t &path);
        int mkdir(const string_t &path);
        int touch(const string_t &path);
        int func(const string_t &path, vfs_func_t *f);
        int rm(const string_t &path);
        int rm_safe(const string_t &path);

        static void split_path(const string_t &path, std::vector<string_t> &args, char c);
        static string_t get_filename(const string_t &path);

    private:
        vfs_node::ref new_node(vfs_file_t type);
        vfs_node::ref get_node(const string_t &path) const;
        int _mkdir(const string_t &path, vfs_node::ref &cur);
        void _touch(vfs_node::ref &node);

        string_t combine(const string_t &pwd, const string_t &path) const;
        int macro(const std::vector<string_t> &m, const vfs_node::ref &node, vfs_node_dec **dec) const;
        void ll(const string_t &name, const vfs_node::ref &node, std::ostream &os) const;

        void error(const string_t &);

        static time_t now();

        char* file_time(const time_t &t) const;
        bool can_rm(const vfs_node::ref &node) const;
        bool can_mod(const vfs_node::ref &node, int mod) const;

    private:
        std::vector<vfs_user> account;
        std::shared_ptr<vfs_node> root;
        int current_user;
        int last_user;
        string_t pwd;
        int year{0};
    };
}

#endif //CLIBPARSER_CVFS_H
