<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/marshmll/e6502">
    <img src="https://raw.githubusercontent.com/marshmll/e6502/main/images/logo.png" alt="Logo" width="400" height="auto">
  </a>

  <h3 align="center">MOS 6502 Emulator - Codename "E6502"</h3>

  <p align="center">
    A MOS 6502 CPU emulator built with C++
    <br />
    <a href="https://github.com/marshmll/e6502"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/marshmll/e6502">View Demo</a>
    •
    <a href="https://github.com/marshmll/e6502/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
  </p>
</div>


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#configurating-and-running">Configurating and running</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#running-the-project">Running the project</a></li>
        <li><a href="#creating-your-own-rom">Creating your own ROM</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<!-- ABOUT THE PROJECT -->
## About The Project

[![E6502][cover]](https://github.com/marshmll/e6502)

The E6502 emulator is a MOS 6502 CPU emulator that runs its instructions sets, emulates it's addressing modes, flags and every other functional aspect of the processor.

The 6502 is a very famous and versatile processor, used in many known applications in the 70-80's, as NES and Atari.

The processor works with a 16 bit memory bus width, supporting max 64 KiB memory size, though it's full capacity is rarely used. The E6502 Emulator also implements a ROM emulation with configurable memory size.

E6502 implements all 56 official instructions with all addressing modes, and soon will be able to handle illegal (non-official) instructions/opcodes.

### Built With

This project was built with:

* [![C++][C++]][C++-url]

## Configurating and running

This project has shell scripts to help building the project. **It is recommended to use a Debian-based distro** to run this project, although it is possible to build and use in any other platform that supports at leas C++ 17.

This manual covers only Debian-based GNU/Linux distros.

### Prerequisites

Install these dependencies in your machine.
* Git
  ```sh
  sudo apt-get install git
  ```
* CMake
  ```sh
  sudo apt-get install cmake
  ```
* G++
  ```sh
  sudo apt-get install g++
  ```

### Running the project

1. Run ```./debug.sh``` or the ```./release.sh``` script, if you want either the Debug or the Release mode build.
2. Wait for the project to build. It may take a while.
3. When the code is built, the shell script will automatically run the executable.

### Creating your own ROM

In the ```kernel``` folder, there is a sample of 6502 Assembly code and its compiled binary. To create your own ROM, it is recommended to use the [vasm](http://sun.hasenbraten.de/vasm/) assembler with old style mode configured.

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Top contributors:

<a href="https://github.com/marshmll/e6502/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=marshmll/e6502" alt="contrib.rocks image" />
</a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Renan Andrade - [Instagram](https://instagram.com/renan._.and) - renandasilvaoliveiraandrade@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/marshmll/e6502.svg?style=for-the-badge
[contributors-url]: https://github.com/marshmll/e6502/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/marshmll/e6502.svg?style=for-the-badge
[forks-url]: https://github.com/marshmll/e6502/network/members
[stars-shield]: https://img.shields.io/github/stars/marshmll/e6502.svg?style=for-the-badge
[stars-url]: https://github.com/marshmll/e6502/stargazers
[issues-shield]: https://img.shields.io/github/issues/marshmll/e6502.svg?style=for-the-badge
[issues-url]: https://github.com/marshmll/e6502/issues
[license-shield]: https://img.shields.io/github/license/marshmll/e6502.svg?style=for-the-badge
[license-url]: https://github.com/marshmll/e6502/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/renan-oliveira-andrade
[cover]: https://raw.githubusercontent.com/marshmll/e6502/main/images/screenshot.png
[C++]: https://img.shields.io/badge/-C++-333333?style=flat&logo=C%2B%2B
[C++-url]: https://en.cppreference.com/w/
[SFML]: https://img.shields.io/badge/-SFML-333333?style=flat&logo=sfml
[SFML-url]: https://www.sfml-dev.org/