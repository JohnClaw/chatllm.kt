#ifndef LIBCHATLLM_H
#define LIBCHATLLM_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    PRINT_CHAT_CHUNK = 0,
    PRINTLN_META = 1,
    PRINTLN_ERROR = 2,
    PRINTLN_REF = 3,
    PRINTLN_REWRITTEN_QUERY = 4,
    PRINTLN_HISTORY_USER = 5,
    PRINTLN_HISTORY_AI = 6,
    PRINTLN_TOOL_CALLING = 7,
    PRINTLN_EMBEDDING = 8,
    PRINTLN_RANKING = 9,
    PRINTLN_TOKEN_IDS = 10
} PrintType;

typedef struct ChatllmObj ChatllmObj;

typedef void (*ChatllmPrintProc)(void* user_data, PrintType print_type, const char* utf8_str);
typedef void (*ChatllmEndProc)(void* user_data);

ChatllmObj* chatllm_create();
void chatllm_append_param(ChatllmObj* obj, const char* utf8_str);
int chatllm_start(ChatllmObj* obj, ChatllmPrintProc f_print, ChatllmEndProc f_end, void* user_data);
void chatllm_set_gen_max_tokens(ChatllmObj* obj, int gen_max_tokens);
void chatllm_restart(ChatllmObj* obj, const char* utf8_sys_prompt);
int chatllm_user_input(ChatllmObj* obj, const char* utf8_str);
int chatllm_set_ai_prefix(ChatllmObj* obj, const char* utf8_str);
int chatllm_tool_input(ChatllmObj* obj, const char* utf8_str);
int chatllm_tool_completion(ChatllmObj* obj, const char* utf8_str);
int chatllm_text_tokenize(ChatllmObj* obj, const char* utf8_str);
int chatllm_text_embedding(ChatllmObj* obj, const char* utf8_str);
int chatllm_qa_rank(ChatllmObj* obj, const char* utf8_str_q, const char* utf8_str_a);
int chatllm_rag_select_store(ChatllmObj* obj, const char* name);
void chatllm_abort_generation(ChatllmObj* obj);
void chatllm_show_statistics(ChatllmObj* obj);
int chatllm_save_session(ChatllmObj* obj, const char* utf8_str);
int chatllm_load_session(ChatllmObj* obj, const char* utf8_str);

#endif // LIBCHATLLM_H