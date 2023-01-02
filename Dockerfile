FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
        && sed -i 's/security.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list

RUN apt-get update && apt-get -y install build-essential uuid-dev iasl nasm gcc-aarch64-linux-gnu \
        python3 python3-distutils python3-pil python3-git python3-pip gettext locales wine\
        gnupg ca-certificates python3-venv git git-core clang llvm curl nano vim 

RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
RUN echo "deb https://download.mono-project.com/repo/ubuntu stable-focal main" | tee /etc/apt/sources.list.d/mono-official-stable.list
RUN curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -
RUN curl https://packages.microsoft.com/config/ubuntu/20.04/prod.list | tee /etc/apt/sources.list.d/microsoft.list

RUN apt-get update && apt-get -y install mono-devel powershell

ENV CLANG38_BIN /usr/lib/llvm-10/bin/
ENV CLANG38_AARCH64_PREFIX aarch64-linux-gnu-
RUN update-alternatives --install /usr/bin/objcopy objcopy /bin/aarch64-linux-gnu-objcopy 70

RUN rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8
ENV LANG en_US.utf8
WORKDIR /build
COPY . .

RUN pip install --upgrade -r pip-requirements.txt && git config --global --add safe.directory '*'

CMD ["/bin/bash"]
