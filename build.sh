# Linux build

set -o errexit

# make c files
make

# copy man page to its directory
cp ./mySort.1.gz /usr/share/man/man1/mySort.1

# refresh man database
sudo mandb

# add executable to /usr/bin
cp ./mySort /usr/bin/mySort

# refresh bash
source ~/.bashrc

echo "Done."