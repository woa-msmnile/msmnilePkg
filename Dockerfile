FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
        && sed -i 's/security.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list

RUN apt update -y && \ 
    apt upgrade -y && \
    apt -y install python3-venv pip git build-essential nuget build-essential uuid-dev \
                iasl nasm gcc-aarch64-linux-gnu python3.10 python3-distutils python3-git python3-pip \
                gettext locales gnupg ca-certificates python3-venv git git-core clang llvm curl mono-devel lld

# ENV CLANGDWARF_BIN /usr/lib/llvm-38/bin/
# ENV CLANGDWARF_AARCH64_PREFIX aarch64-linux-gnu-
RUN update-alternatives --install /usr/bin/objcopy objcopy /bin/aarch64-linux-gnu-objcopy 70

RUN rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8
ENV LANG en_US.utf8
WORKDIR /build
COPY . .

RUN pip install --upgrade -r pip-requirements.txt && git config --global --add safe.directory '*'

CMD ["/bin/bash"]
