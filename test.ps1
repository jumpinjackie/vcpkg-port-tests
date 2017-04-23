$vcpkg_root = "D:\Workspace\vcpkg"
$vcpkg_toolchain = "$vcpkg_root\scripts\buildsystems\vcpkg.cmake"

$pwd = Convert-Path .

$configs = @{}
$configs["x86_debug"] = @("Visual Studio 15 2017", "Debug")
$configs["x86_release"] = @("Visual Studio 15 2017", "Release")
$configs["x64_debug"] = @("Visual Studio 15 2017 Win64", "Debug")
$configs["x64_release"] = @("Visual Studio 15 2017 Win64", "Release")

$testapps = @{}
$testapps["libgd"] = "gdtest"
$testapps["xalan-c"] = "xalantest"
$testapps["xerces-c"] = "xercestest"
$testapps["geos"] = "geostest"
$testapps["gdal"] = "gdaltest"

# CMake prepare
$configs.keys | ForEach-Object {
    $confKey = $_
    $values = $configs[$confKey]
    $cmake_gen = $values[0]
    $config = $values[1]
    Write-Host "[cmake]: Prepare $confKey"
    &cmake "-Bbuild/$confKey" `-G "$cmake_gen"` "-DCMAKE_TOOLCHAIN_FILE=$vcpkg_toolchain" "-DCMAKE_BUILD_TYPE=$config" "-H."
    if ($?) {
        Write-Host "[cmake]: Prepare OK"
    } else {
        Write-Host "[cmake]: Prepare FAIL"
        Set-Location $pwd
        exit 1
    }
}

# CMake build
$configs.keys | ForEach-Object {
    $confKey = $_
    $values = $configs[$confKey]
    $cmake_gen = $values[0]
    $config = $values[1]
    Write-Host "[cmake]: Build $confKey"
    &cmake --build build/$confKey --config $config
    if ($?) {
        Write-Host "[cmake]: Prepare OK"
    } else {
        Write-Host "[cmake]: Prepare FAIL"
        Set-Location $pwd
        exit 1
    }
}

# Test our programs
$configs.keys | ForEach-Object {
    $confKey = $_
    $values = $configs[$confKey]
    $cmake_gen = $values[0]
    $config = $values[1]
    Write-Host "[cmake]: Testing apps under $confKey"

    $testapps.keys | ForEach-Object {
        $port = $_
        $app = $testapps[$port]
        $exe = ".\$app.exe"
        Write-Host "[test]: $app for ($port - $confKey)"
        Set-Location -Path $pwd/build/$confKey/out/$app/bin/$config
        & $exe
        if ($?) {
            Write-Host "[test]: OK"
        } else {
            Write-Host "[test]: FAIL"
            Set-Location $pwd
            exit 1
        }
    }
}

Set-Location -Path $pwd