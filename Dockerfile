FROM gcc
COPY . /usr/src/cube
WORKDIR /usr/src/cube
RUN make
RUN make tests
CMD ["./welcome.sh"]