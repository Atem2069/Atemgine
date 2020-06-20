# Atemgine
Heavily WIP interface based renderer. 

Currently the renderer is designed to be API agnostic - at least between modern APIs i.e. D3D11/12,Vulkan etc. - though it currently has a very WIP D3D11 backend.
Makes use of inheritance with each major object having three different 'building blocks'
  - Purely virtual base class which describes basic API agnostic methods with no implementation
  - API specific implementation - has protected 'API' methods in order to do API specific tasks
  - API agnostic implementation - calls the API specific code depending on which API is being used - and is the interface exposed to a developer
