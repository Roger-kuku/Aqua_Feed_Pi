# Aqua Matic  

Aqua Matic, developed by Team 35, is a smart aquarium management system designed to help fish owners efficiently care for their aquatic pets even when physically unavailable. The system addresses common challenges such as feeding fish on time and monitoring crucial water parameters like oxygen (O2) and pH levels. By automating these tasks and utilizing real-time data, Aqua Matic ensures a healthier and more manageable aquatic environment.  

The project stems from the need to solve three primary issues: the difficulty of feeding fish when busy or absent, the inability to track tank conditions, and the challenge of identifying fish hunger patterns. Aqua Matic provides a solution by integrating advanced technology, including WebSockets for real-time communication between components and a predictive hunger detection mechanism based on O2 sensor data.  

The system architecture comprises three main components: the FishFeederSystem, FeedController, and SensorDataLogger. The FishFeederSystem automates the feeding process, while the FeedController manages feeding schedules and controls. The SensorDataLogger continuously monitors and records key tank parameters, offering valuable insights into the aquarium's environment.  

Aqua Matic leverages C++ for hardware integration and backend development, making the system efficient and responsive. WebSockets are employed to maintain real-time communication between the hardware and the control interface. The modular architecture allows for easy expansion and customization, ensuring compatibility with additional sensors or features as needed.  

The setup components include sensors for monitoring oxygen and pH levels, a Raspberry Pi for data processing and system management, and actuators for the automatic fish feeding mechanism. The system follows a structured flow, beginning with receiving feeding requests from users or detecting hunger through sensor data. This data is then processed by the FishFeederSystem, which executes feeding operations and logs information through the SensorDataLogger.  

Aqua Matic represents an innovative step forward in aquarium automation, offering a reliable and user-friendly solution for fish care. Thank you for your interest in this project by Team 35.
