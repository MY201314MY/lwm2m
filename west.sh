path=`pwd`

west build -b qemu_x86 --no-sysbuild -DCONF_FILE:STRING="${path}/prj.conf"

