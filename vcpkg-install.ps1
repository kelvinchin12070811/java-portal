$dependencies = @(
    'boost-program-options',
    'fmt',
    'nlohmann-json',
    'restclient-cpp'
)

Write-Host 'Package(s) to install:'
Write-Host ($dependencies -join ', ')

foreach ($dependency in $dependencies) {
    Write-Host ''
    Write-Host "Installing" $dependency"..."
    .\vcpkg\vcpkg.exe "install" $dependency
}

Write-Host ''
Write-Host "All done!"