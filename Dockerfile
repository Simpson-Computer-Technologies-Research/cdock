# Dockerfile for C
FROM gcc:latest

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# To build the image, run the following command in the directory containing the Dockerfile
# docker build -t cdocker .

# To run the container, run the following command
# docker run -it --rm --name cdocker cdocker
