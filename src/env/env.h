#ifndef MS_ENV_H_
#define MS_ENV_H_

#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} env_entry_t;

typedef struct {
    uint64_t num_entry;
    env_entry_t *entries;
} env_t;

env_t clone_original_env(const char **envp);
env_entry_t *get_entry_from_key(const env_t *env, const char *key);
void add_env_entry(env_t *env, env_entry_t entry);
void print_env(const env_t *env);
void destroy_env(env_t *env);

#endif /* MS_ENV_H_ */
