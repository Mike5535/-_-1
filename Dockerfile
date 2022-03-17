FROM gcc:latest
RUN apt update -y && \
    apt install -y cppcheck clang-tidy python3-pip libc6-dbg cmake libgtest-dev
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y Cmake && rm -rf /var/lib/apt/lists/*
RUN apt update && apt install -y valgrind && rm -rf /var/lib/apt/lists/*
RUN pip install cpplint
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install
