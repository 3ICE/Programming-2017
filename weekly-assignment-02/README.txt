TIE-02206 Basic Course on Programming spring 2017 – excercise 02
Daniel "3ICE" Berezvai
Student number: 262849

What is the difference between a class and an object?
An object is an INSTANCE of a class. Everyone knowws that. But what does it mean? You can instantiate classes into objects — you can create objects based on a class "template".
Class is stateless (unless singleton) while objects have a state (properties with values defined).
Objects also have limited lifespans most of the time. On the other hand, classes do not usually get destroyed before the end of the program. (You can hack it, but why would you? Unless you create thousands of dynamically generated classes.)
Advanced programmers can generate more or less accurate class descriptors from a given object (in memory or from a dump file, etc.), this is done through reverse engineering.

What is public interface?
A surface through which we can control members of the class. It can have getters, setters, other accessors, methods, functions, operations, etc.
Interaction between members of the class is possible through functions defined in the interface. Example: time3 = time1.add(time2) will initialize the value of time3 to be the sum of time1 and time2. Or: date.add(date2) will set date to date+date2. (Be careful your methods behave in a more logical way, so like this.)

What is private interface?
A place for all the class properties, temporary variables, and helper functions, that are supposed to be hidden from the public eye.
Private properties can still be accessed through some light hacking. This therefore is not a true protection for our members, just an open-ended contract between honest API users and developers — not to touch code unintended for consumption.