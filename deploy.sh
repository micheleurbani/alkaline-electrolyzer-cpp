docker build -t alkaline .
docker run -d --name alkaline alkaline
docker cp alkaline:/app/build/alkalineElectrolyzer.fmu .
docker stop alkaline
docker rm alkaline