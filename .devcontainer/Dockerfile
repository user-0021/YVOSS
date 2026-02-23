FROM ubuntu:24.04

RUN apt-get update -yqq \
    && apt-get install -yqq --no-install-recommends software-properties-common \
    sudo curl wget cmake make pkg-config locales git gcc-13 g++-13 \
    openssl libssl-dev libjsoncpp-dev uuid-dev zlib1g-dev libc-ares-dev language-pack-ja\
    postgresql-server-dev-all libmariadb-dev libsqlite3-dev libhiredis-dev clang libclang-dev\
		&& add-apt-repository ppa:leaningtech-dev/cheerp-nightly-ppa \
		&& apt-get update -yqq \
		&& apt-get install cheerp-core \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen ja_JP.UTF-8

RUN git clone https://github.com/drogonframework/drogon.git /tmp/drogon && \
    cd /tmp/drogon && \
    git submodule update --init && \
    mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/drogon
