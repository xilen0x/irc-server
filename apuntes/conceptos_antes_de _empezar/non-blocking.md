# Non-blocking

## Non-blocking [What is a file descriptor?](https://www.lenovo.com/us/outletus/en/glossary/file-descriptor/?orgRef=https%253A%252F%252Fwww.google.com%252F)


- **Can I manipulate the properties of a file descriptor?**
    - Yes, you can manipulate the properties of a file descriptor using various operations. For example, you can change the file descriptor's position within a file using the lseek() function, set it to **non-blocking** mode to enable asynchronous I/O, or change its permissions using the fcntl() function. These operations allow you to control and customize how you interact with the file or I/O resource.

- **What happens if I try to read from a file descriptor that has no data available?**
    - If you try to read from a file descriptor that has no data available, the behavior depends on whether the file descriptor is set to blocking or **non-blocking** mode. In blocking mode, the read operation will block the program's execution until data becomes available. In **non-blocking** mode, the read operation will return immediately with an error code showing that no data is currently available. It's important to handle such cases appropriately in your code to avoid blocking indefinitely or missing data.

- **Can I use file descriptors with network sockets?**
    - Yes, file descriptors can be used with network sockets. In fact, network sockets are often represented by file descriptors in many operating systems. This allows you to use file I/O operations on network sockets, making it easier to handle network communication using the same file descriptor-based programming model. With file descriptors, you can read data from a socket, write data to a socket, or perform other socket-related operations.

- **Can I perform *non-blocking* I/O operations with file descriptors?**
    - Yes, you can perform **non-blocking** I/O operations with file descriptors. By setting a file descriptor to **non-blocking** mode using functions like fcntl(), you can enable **non-blocking** I/O. In **non-blocking** mode, I/O operations will not block the program's execution if data is not immediately available. Instead, the operations will return immediately, allowing your program to continue executing and check for data availability later. This is useful for implementing asynchronous or event-driven programming models.

