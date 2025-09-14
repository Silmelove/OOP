# Transport Management System – Documentation
## 1.Object-Oriented Analysis (OOA)
1.1 Problem Domain :
 Xây dựng hệ thống quản lý phương tiện giao thông, trong đó mỗi loại phương tiện có thông tin riêng và được quản lý tập trung.

1.2 Main Entities:
- Vehicle (route, capacity, booked, status)
- ExpressBus (specialized vehicle with higher speed)
- Passenger (name, ticket ID)
- Schedule (departureTime, arrivalTime, assignedVehicle)
- Station (name, location, list of schedules)

1.3 Relationships:
- Inheritance: ExpressBus → Vehicle
- Aggregation:
  * Station contains multiple Schedules
  * Schedule contains a Vehicle
  * Vehicle can contain Passengers

Use Cases:
1.Passenger booking seats on Vehicle
2.Vehicle calculating travel time
3.Station managing schedules
4.Displaying information for each entity


## 2. Class Design & Inheritance Explanation
2.1 Vehicle (Base Class):
Defines shared attributes (route, capacity, booked seats, status).
Provides methods like calculateTravelTime(), bookPassenger(), displayInfo().

2.2 ExpressBus (Derived Class):
Specialization of Vehicle with higher speed.
Overrides calculateTravelTime() to use different speed.
Demonstrates Polymorphism: same interface but different behavior.

2.3 Passenger:
Simple class for storing passenger data (name, ticketID).

2.4 Schedule:
Manages departure and arrival times, with an assigned vehicle.

2.5 Station:
Holds a collection of schedules (composition).

3. Code Walkthrough
Key Points:

3.1 Virtual Functions:
calculateTravelTime() is virtual in Vehicle, overridden in ExpressBus.

3.2 Booking Logic:
Prevents overbooking by checking booked < capacity.

3.3 Aggregation:
Station contains vector of Schedule.
Output Functions:
Each class has displayInfo() for encapsulated printing.

## 4. Test Results (Sample Output)
1. Explanation:
<img width="692" height="141" alt="image" src="https://github.com/user-attachments/assets/0d92b1af-5145-4220-818f-17aa10495b96" />

- Vehicle v1 is created with route City-A → City-B, capacity 3 passengers.
- ExpressBus eb1 is created with route City-C → City-D, capacity 2 passengers, speed 80 km/h.
- This proves that the Vehicle class and the ExpressBus derived class display the correct information.

2. Explanation:
<img width="517" height="178" alt="image" src="https://github.com/user-attachments/assets/46a4345c-3043-4102-9db3-550dd1a9c1d0" />

- Four passengers are created with corresponding names and IDs.
- This shows that the Passenger class is initialized and displaying the correct information.
3. Explanation:

<img width="692" height="298" alt="image" src="https://github.com/user-attachments/assets/2f2c394e-1a6f-4c6a-b270-01702562933b" />

- Vehicle v1 has capacity 3 → Alice, Bob, Charlie successfully book tickets, but David fails (logically “full”).
- ExpressBus eb1 has capacity 2 → Alice, Bob successfully book tickets, Charlie fails (logically correct).
- This proves that the bookPassenger() method works correctly.

4. Explanation:
<img width="693" height="104" alt="image" src="https://github.com/user-attachments/assets/5cb5ddb8-def3-4f10-9ada-c447f829e67d" />


- Vehicle default speed 50 km/h → 100 / 50 = 2 hours.
- ExpressBus speed 80 km/h → 100 / 80 = 1.25 hours.
- This confirms the calculateTravelTime() method calculates correctly.
5. Explanation:

<img width="692" height="386" alt="image" src="https://github.com/user-attachments/assets/73e5c0c6-db5b-4b3a-a591-1f9c85023928" />

- You can add up to 10 schedules to a Station.
- When running, we see that Schedule 1 → Schedule 10 are all added successfully.
- When trying to add Schedule 11, the program reports an error:


Schedule list in Station:
- Central Station (Downtown) contains 10 schedules:
- The first 2 schedules are 08:00-10:00 (Regular Vehicle) and 09:00-11:00 (ExpressBus).
- The remaining schedules (12:00-14:00) all share the City-A to City-B route.
- Each schedule clearly displays: departure time, arrival time, bus route, capacity, number of tickets booked, status (On-time), speed (if ExpressBus).

5. LLM Usage
------------
How I Used LLM (ChatGPT):
- I used ChatGPT to brainstorm inheritance hierarchy and check if my design made sense.
- Prompt Example:
  "Suggest inheritance hierarchies for vehicles in a transportation system."
- ChatGPT suggested creating a base Vehicle and specialized classes like ExpressBus.
  I customized these ideas for my scenario.
- I also asked ChatGPT for a code review, which helped me see missing details
  (like linking Passenger list with Vehicle).
- Important: I wrote all the code myself. The LLM was used as a supportive tool,
  not to generate the full assignment.
"""
