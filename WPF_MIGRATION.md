# WPF Migration Setup

This repository now contains a mixed Visual Studio solution:

- `CalculatorUI`: .NET 8 WPF frontend.
- `CalculatorCore`: native C DLL bridge exposing a stable P/Invoke ABI.

## Build Requirements

Install Visual Studio 2022 with these workloads/components:

- .NET desktop development
- Desktop development with C++
- Windows 10 or Windows 11 SDK
- MSVC v143 toolset

The .NET CLI can build `CalculatorUI`, but the full solution requires Visual Studio/MSBuild with native C++ targets because `CalculatorCore.vcxproj` imports `Microsoft.Cpp.Default.props`.

## Build Order

Open `Calculator.sln` in Visual Studio and build `Debug|x64`.

The solution is configured so `CalculatorUI` depends on `CalculatorCore`. The native project post-build copies:

- `CalculatorCore.dll`
- any `gsl*.dll` files beside the native output
- `saves.dat`

into:

```text
CalculatorUI/bin/x64/Debug/net8.0-windows/
```

## GSL Note

The current `gsl` folder contains vendored source/header files, but no `.lib` or `.dll` binaries. If your existing native build links prebuilt GSL binaries, add their `.lib` files to `CalculatorCore` linker input and ensure their `.dll` files are copied beside `CalculatorUI.exe`.

If you want a single native DLL with no extra GSL runtime DLLs, build/link GSL statically into `CalculatorCore`.

## Native ABI

The exported ABI is declared in:

```text
CalculatorCore/calculator_api.h
```

The WPF P/Invoke mappings are in:

```text
CalculatorUI/Interop/NativeMethods.cs
```

Keep this boundary small and stable. Do not marshal internal calculator structs that contain pointers, Windows handles, or heap-owned arrays directly into C#.
