FROM gcc:4.9
COPY . /usr/src/cube
WORKDIR /usr/src/cube
RUN make
CMD ["/usr/src/cube/bin/Rubiks"]