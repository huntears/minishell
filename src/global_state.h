#ifndef MS_GLOBAL_STATE_H_
#define MS_GLOBAL_STATE_H_

#ifndef MS_MAX_PATH_SIZE
#define MS_MAX_PATH_SIZE 1024
#endif

typedef struct {
    char current_path[MS_MAX_PATH_SIZE];
    char previous_path[MS_MAX_PATH_SIZE];
} global_state_t;

extern global_state_t g_state;

typedef struct env env_t;
void init_global_state(env_t *env);

#endif /* MS_GLOBAL_STATE_H_ */
