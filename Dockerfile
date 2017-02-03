FROM gcc
COPY . /usr/src/cube
WORKDIR /usr/src/cube
RUN make
RUN make tests
CMD ["/usr/src/cube/test/run_tests"]