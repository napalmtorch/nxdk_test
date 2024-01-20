clear
cd /mnt/d/projects/nxdk_test

../nxdk/bin/activate &
echo "Spawned NXDK shell instance"

sh "build_shader.sh"

make
echo "Finished building game, launching XEMU..."

/mnt/d/projects/nxdk_test/xemu.exe -device lpc47m157 -serial stdio -dvd_path Minecraft.iso