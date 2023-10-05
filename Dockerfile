FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y apt-utils 2>&1 | \
    grep -v "^debconf: delaying package configuration, since apt-utils.*"
RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
        && sed -i 's/security.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
RUN apt update && apt install -y python3.10-minimal
RUN apt-get update && apt-get -y install build-essential uuid-dev iasl nasm gcc-aarch64-linux-gnu \
        python3 python3-distutils python3-pil python3-git python3-pip gettext locales \
        gnupg ca-certificates python3-venv git git-core clang llvm curl nano

ENV CLANG38_BIN /usr/lib/llvm-14/bin/
ENV CLANG38_AARCH64_PREFIX aarch64-linux-gnu-
RUN update-alternatives --install /usr/bin/objcopy objcopy /bin/aarch64-linux-gnu-objcopy 70

RUN rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8
ENV LANG en_US.utf8
WORKDIR /build
COPY . .

RUN pip install --upgrade -r pip-requirements.txt && git config --global --add safe.directory '*'

CMD ["/bin/bash"]
