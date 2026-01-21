FROM debian:bookworm
RUN apt-get update && apt-get install -y build-essential cmake git
COPY . /source
WORKDIR /source
RUN cmake -B mayhem -DSANITIZE="address" .
RUN cmake --build mayhem --target full-stack
