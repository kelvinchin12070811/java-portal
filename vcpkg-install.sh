dependencies=(
    "boost-program-options"
    "boost-scope-exit"
    "fmt"
    "nlohmann-json"
    "restclient-cpp"
)

for dependency in ${dependencies[@]}
do
    echo ""
    echo "Installing ${dependency}..."
    ./vcpkg/vcpkg install $dependency
done

echo ""
echo "All done!"