#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types
typedef char *string;

// Global definitions
#define error_message "Not enough arguments provided. Examples:\n$ cdock new {name}\n$ cdock start {name}\n$ cdock rmcontainer {name}\n$ cdock rmimage {name}\n\nNote: You must have a Dockerfile in the working directory if running/building an image/container!\n"
#define base_cmd_run "docker run -it --rm --name "
#define base_cmd_build "docker build -t "
#define base_cmd_delete_image "docker rmi "
#define base_cmd_delete_container "docker rm "

// Function prototypes
void build_image(string);
void build_container(string);
void delete_image(string);
void delete_container(string);

void command_start(string);
void command_new(string);

int streq(string, string);

// Main function
int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("%s", error_message);
    return 1;
  }

  string command = argv[1];
  string name = argv[2];

  if (streq(command, "new"))
  {
    command_new(name);
  }
  else if (streq(command, "start"))
  {
    command_start(name);
  }
  else if (streq(command, "rmcontainer"))
  {
    delete_container(name);
  }
  else if (streq(command, "rmimage"))
  {
    delete_image(name);
  }
  else
  {
    printf("%s", error_message);
  }

  return 0;
}

/**
 * Check if two strings are equal
 * @param s1 The first string
 * @param s2 The second string
 * @return 1 if equal, 0 if not
 */
int streq(string s1, string s2)
{
  return strcmp(s1, s2) == 0;
}

/**
 * Run the start command
 * @param name The container name
 */
void command_start(string name)
{
  printf("Building/Running container %s\n", name);
  build_container(name);
}

/**
 * Run the new command
 * @param name The image name
 */
void command_new(string name)
{
  printf("Building image %s\n", name);
  build_image(name);

  command_start(name);
}

/**
 * Build a new image
 * @param name The image name
 */
void build_image(string name)
{
  string build = base_cmd_build;
  string build_command = malloc(strlen(build) + strlen(name) + 2);

  // Size of: strlen(build)
  strcpy(build_command, build);

  // Size of: strlen(name)
  strcat(build_command, name);

  // Size of: + 2
  strcat(build_command, " .");

  // Execute the command
  system(build_command);
}

/**
 * Build a new container
 * @param name The container name
 */
void build_container(string name)
{
  string run = base_cmd_run;
  string run_command = malloc(strlen(run) + strlen(name) * 2 + 2);

  // Size of: strlen(run)
  strcpy(run_command, run);

  // Size of: strlen(name) * 2
  strcat(run_command, name);
  strcat(run_command, " ");
  strcat(run_command, name);

  // Execute the command
  system(run_command);
}

/**
 * Delete an image
 * @param name The image name
 */
void delete_image(string name)
{
  string delete = base_cmd_delete_image;
  string delete_command = malloc(strlen(delete) + strlen(name) + 2);

  // Size of: strlen(delete)
  strcpy(delete_command, delete);

  // Size of: strlen(name)
  strcat(delete_command, name);

  // Execute the command
  system(delete_command);
}

/**
 * Delete a container
 * @param name The container name
 */
void delete_container(string name)
{
  string delete = base_cmd_delete_container;
  string delete_command = malloc(strlen(delete) + strlen(name) + 2);

  // Size of: strlen(delete)
  strcpy(delete_command, delete);

  // Size of: strlen(name)
  strcat(delete_command, name);

  // Execute the command
  system(delete_command);
}