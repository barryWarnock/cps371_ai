FROM gcc
COPY . /usr/src/cube
WORKDIR /usr/src/cube
RUN make
CMD ["/usr/src/cube/bin/Rubiks"]