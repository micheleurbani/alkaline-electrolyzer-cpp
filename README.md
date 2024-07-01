# FMU4cpp (early prototype)

## Get started

Build Docker image to have a vanilla Ubuntu 20.04 installation with glibc6, cmake and g++.

```bash
docker build -t alkaline .
```

Then run a docker container and copy the FMU locally. The following is a
for the CLI instruction

```bash
docker run -it --name FMUgenerator alkaline
```

If you launch the container twice, remember to remove the old one.

```bash
docker rm FMUgenerator
```

When the container is running, copy the FMU locally.

```bash
docker cp FMUgenerator:/app/build/alkalineElectrolyzer.fmu
```

### Requirements
* C++17 compiler
* CMake >= 3.15
