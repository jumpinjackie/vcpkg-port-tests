$vcpkg_root = "D:\Workspace\vcpkg"
$vcpkg_toolchain = "$vcpkg_root\scripts\buildsystems\vcpkg.cmake"

$pwd = Convert-Path .

$configs = @{}
$configs["x86_debug"] = @("Visual Studio 15 2017", "Debug", $False)
$configs["x86_release"] = @("Visual Studio 15 2017", "Release", $False)
$configs["x64_debug"] = @("Visual Studio 15 2017 Win64", "Debug", $False)
$configs["x64_release"] = @("Visual Studio 15 2017 Win64", "Release", $False)
$configs["x86_debug_static"] = @("Visual Studio 15 2017", "Debug", $True, "x86-windows-static")
$configs["x86_release_static"] = @("Visual Studio 15 2017", "Release", $True, "x86-windows-static")
$configs["x64_debug_static"] = @("Visual Studio 15 2017 Win64", "Debug", $True, "x64-windows-static")
$configs["x64_release_static"] = @("Visual Studio 15 2017 Win64", "Release", $True, "x64-windows-static")

$testapps = @{}
$testapps["libgd"] = @("gdtest", $False)
$testapps["xalan-c"] = @("xalantest", $False)
$testapps["xerces-c"] = @("xercestest", $False)
$testapps["geos"] = @("geostest", $False)
$testapps["gdal"] = @("gdaltest", $False)
$testapps["podofo"] = @("podofotest", $True)
$testapps["cppunit"] = @("unittest", $True)

# CMake prepare
$configs.keys | ForEach-Object {
    $confKey = $_
    $values = $configs[$confKey]
    $cmake_gen = $values[0]
    $config = $values[1]
    $static = $values[2]
    Write-Host "[cmake]: Prepare $confKey"
    if ($static) {
        $triplet = $values[3]
        &cmake "-Bbuild/$confKey" `-G "$cmake_gen"` "-DCMAKE_TOOLCHAIN_FILE=$vcpkg_toolchain" "-DTEST_STATIC=1" "-DVCPKG_TARGET_TRIPLET=$triplet" "-DCMAKE_BUILD_TYPE=$config" "-H."
    } else {
        &cmake "-Bbuild/$confKey" `-G "$cmake_gen"` "-DCMAKE_TOOLCHAIN_FILE=$vcpkg_toolchain" "-DCMAKE_BUILD_TYPE=$config" "-H."
    }
    if ($?) {
        Write-Host "[cmake]: Prepare $confKey - OK"
    } else {
        Write-Host "[cmake]: Prepare $confKey - FAIL"
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
        Write-Host "[cmake]: Build $confKey - OK"
    } else {
        Write-Host "[cmake]: Build $confKey - FAIL"
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
    $static = $values[2]
    Write-Host "[cmake]: Testing apps under $confKey"

    $testapps.keys | ForEach-Object {
        $port = $_
        $app = $testapps[$port][0]
        $staticOnly = $testapps[$port][1]
        if ($static -and !$staticOnly) {
            Write-Host "[test]: Skip running $app as it is not built for $confKey"
        } else {
            $exe = ".\$app.exe"
            $outputFile = "${app}_output.txt"
            Write-Host "[test]: $app for ($port - $confKey)"
            Set-Location -Path $pwd/build/$confKey/out/$app/bin/$config
            [string] (& $exe 2>&1) | Out-File $outputFile
            if ($?) {
                Write-Host "[test]: $app - OK"
            } else {
                Write-Host "[test]: $app - FAIL"
                Set-Location $pwd
                exit 1
            }
        }
    }
}

Set-Location -Path $pwd