Set-Location $PSScriptRoot

$BUILD_DIR = "build"
$BUILD_TYPE = "Debug"

# Allow an optional argument for build type
if ($args.Length -gt 0 -and ($args[0] -eq "Release" -or $args[0] -eq "Debug")) {
  $BUILD_TYPE = $args[0]
}

if (-not (Test-Path -Path $BUILD_DIR -PathType Container)) {
  New-Item -Path $BUILD_DIR -ItemType Directory
}

Set-Location $BUILD_DIR

cmake -G "Visual Studio 17 2022" ..
if ($LASTEXITCODE -ne 0) {
  Set-Location $PSScriptRoot
  exit 1
}

cmake --build . --config $BUILD_TYPE --parallel 5
if ($LASTEXITCODE -ne 0) {
  Set-Location $PSScriptRoot
  exit 1
}

Set-Location $PSScriptRoot
exit 0
