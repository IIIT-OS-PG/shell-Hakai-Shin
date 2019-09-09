#ifndef WASHBUILT_HPP
#define WASHBUILT_HPP
//contains all the headers required

int lsh_cd(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {"cd","~"};

int (*builtin_func[]) (char **) = {&lsh_cd};

int lsh_num_builtins();

#endif
