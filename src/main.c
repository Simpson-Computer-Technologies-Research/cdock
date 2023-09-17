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
#define base_cmd_exists_image "docker images -q "

// Function prototypes
int build_image(string);
int build_container(string);
int delete_image(string);
int delete_container(string);
int image_exists(string);

int command_start(string);
int command_new(string);
int command_rmcontainer(string);
int command_rmimage(string);

int streq(string, string);

// Main function
int main(int argc, char **argv)
{
  if (argc < 3)
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
    command_rmcontainer(name);
  }
  else if (streq(command, "rmimage"))
  {
    command_rmimage(name);
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
 * @return 1 if successful, 0 if not
 */
int command_start(string name)
{
  printf("Building/Running container %s\n", name);
  return build_container(name);
}

/**
 * Run the new command
 * @param name The image name
 * @return 1 if successful, 0 if not
 */
int command_new(string name)
{
  // If the image already exists, delete it. If the deletion wasn't
  // successful, exit the program.
  printf("Checking if image %s already exists\n", name);
  if (image_exists(name))
  {
    if (command_rmimage(name))
    {
      printf("Image %s already exists and was unable to be deleted.\n", name);
      return 1;
    }
  }

  // Build the image
  printf("Building image %s\n", name);
  build_image(name);

  // Run the container
  return command_start(name);
}

/**
 * Run the rmcontainer command
 * @param name The container name
 * @return 1 if successful, 0 if not
 */
int command_rmcontainer(string name)
{
  printf("Deleting container %s\n", name);
  return delete_container(name);
}

/**
 * Run the rmimage command
 * @param name The image name
 * @return 1 if successful, 0 if not
 */
int command_rmimage(string name)
{
  printf("Deleting image %s\n", name);
  return delete_image(name);
}

/**
 * Check if an image exists
 * @param name The image name
 * @return 1 if exists, 0 if not
 */
int image_exists(string name)
{
  const char *command = base_cmd_exists_image;
  string command_with_name = malloc(strlen(command) + strlen(name) + 1);

  // Size of: strlen(command)
  strcpy(command_with_name, command);

  // Size of: strlen(name)
  strcat(command_with_name, name);

  // Execute the command
  return system(command_with_name) == 0;
}

/**
 * Build a new image
 * @param name The image name
 * @return 1 if successful, 0 if not
 */
int build_image(string name)
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
  return system(build_command);
}

/**
 * Build a new container
 * @param name The container name
 * @return 1 if successful, 0 if not
 */
int build_container(string name)
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
  return system(run_command);
}

/**
 * Delete an image
 * @param name The image name
 * @return 1 if successful, 0 if not
 */
int delete_image(string name)
{
  string delete = base_cmd_delete_image;
  string delete_command = malloc(strlen(delete) + strlen(name) + 2);

  // Size of: strlen(delete)
  strcpy(delete_command, delete);

  // Size of: strlen(name)
  strcat(delete_command, name);

  // Execute the command
  return system(delete_command) == 0;
}

/**
 * Delete a container
 * @param name The container name
 * @return 1 if successful, 0 if not
 */
int delete_container(string name)
{
  string delete = base_cmd_delete_container;
  string delete_command = malloc(strlen(delete) + strlen(name) + 2);

  // Size of: strlen(delete)
  strcpy(delete_command, delete);

  // Size of: strlen(name)
  strcat(delete_command, name);

  // Execute the command
  return system(delete_command);
}
