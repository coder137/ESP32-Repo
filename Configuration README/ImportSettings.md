### My Configuration

After configuring your `blink` build for the first time

`Note: Look at the Top Level README`

* For the first project do the `Eclipse Configuration` as given in the link above

* After that configuration is done

	* Go to the Project Properties

	* C/C++ Build top level -> Manage Configurations

	* Click New and check Import from Projects

	* Add the configured project specifications here ex. blink > default

	* Save the Configuration Name as ESP32Config

* For every subsequent project that is created after the above step

	* Import template to your folder

	* use `menu makeconfig` to configure your ESP-IDF Build

	* `make all` or `make` this build of your project

	* Import the project to Eclipse

	* open `Makefile` and change PROJECT_NAME to the project name

	`Note: Project Name and Folder name must be the same`

	* Configure your C/C++ Build to ESP32Config

	* Clean and Build your project inside Eclipse
