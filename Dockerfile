FROM ubuntu:20.04

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Update and install some essential packages
RUN apt-get update && apt-get install -y \
    libc6 \
    vim \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY CMakeLists.txt /app
COPY src /app/src
COPY export /app/export
COPY version.txt /app

RUN mkdir -p /app/build && \
    cd /app/build && \
    cmake .. && \
    cmake --build . && \
    make

# Command to run when starting the container
CMD ["bash"]