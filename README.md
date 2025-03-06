# ConveyorBelt
Production line simulator for conveyor belt in factories.
- [x] The program parse a config file
- [x] Display the layout in the terminal
- [ ] Create intelligence for each device
- [ ] Make them able to move item
- [ ] Print every step of the sorting
- [ ] Add the possibility to go forward and backward in the steps
## Configuration File Attributes

The configuration file for the ConveyorBelt project includes the following mandatory attributes. (Format -> "*fileName.factory*"):

- **Name**: The name of the factory. 

- **Type**: The function of the factory (book sorter, Automated Storage).

- **Location**: Where is this marvellous factory.

- **Floor**: The floor where the layout is located.

- **Size**: The size of the factory in terms of dimensions. Format -> "*width x height*".

- **Layout**: The layout of the factory, which includes different elements represented by symbols.
- **Legend**: Name every element written in the layout. Format -> "*symbol = device name*"

**Exemple of output here (screenshot)**

  For this input file :

  ```
  Name      : Encom
  Type      : Sorter factory
  Location  : NY
  Floor     : Ground floor
  Size      : 20x10
  Layout    :
                      
         ---          
     L>S>>>>>    >>>X 
            >    >    
           ->    >    
           ->    >    
           ->    >    
           ->    >    
            >>>>>>    
                      
  
  Legend:
  L = launcher
  S = scanner
  - = rack
  > = Conveyor belt
  X = trash
  ```
  
  The output will looks like :
  
  ![image](https://github.com/user-attachments/assets/b8ced641-bf4c-4530-bf48-15205285edb8)

