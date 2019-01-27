//
// Project: clibparser
// Created by bajdcc
//

// 中断表（本文件可不包含，只为了说明）

enum INTR_TABLE {
    INTR_PUT_CHAR = 0,
    INTR_PUT_NUMBER = 1,
    INTR_PUT_HEX = 2,
    INTR_INPUT_LOCK = 10,
    INTR_INPUT_CHAR = 11,
    INTR_INPUT_STOP = 12,
    INTR_INPUT_STATE = 13,
    INTR_RESIZE = 20,
    INTR_MALLOC = 30,
    INTR_FREE = 31,
    INTR_PUT_EXEC_CHAR = 50,
    INTR_PUT_EXEC_FILE = 51,
    INTR_PUT_EXEC_WAIT = 52,
    INTR_PUT_EXEC_SLEEP = 53,
    INTR_PUT_EXEC_WAKEUP = 54,
    INTR_PUT_FORK = 55,
    INTR_PUT_IO_CONNECT = 56,
    INTR_PUT_KILL_CHILDREN = 57,
    INTR_SLEEP_RECORD = 100,
    INTR_SLEEP_REACH = 101,
};
