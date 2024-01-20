./../nxdk/tools/cg/linux/cgc -profile vp20 -o "assets/shaders/vertex.cgs" "assets/shaders/vertex.cg"
./../nxdk/bin/vp20compiler "assets/shaders/vertex.cgs" > "assets/shaders/vertex.inl"
#rm "assets/shaders/vertex.cgs"
echo "Compiled vertex shader"

./../nxdk/tools/cg/linux/cgc -profile fp20 -o "assets/shaders/pixel.cgs" "assets/shaders/pixel.cg"
./../nxdk/bin/fp20compiler "assets/shaders/pixel.cgs" > "assets/shaders/pixel.inl"
rm "assets/shaders/pixel.cgs"
echo "Compiled pixel/fragment shader"