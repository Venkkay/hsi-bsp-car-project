# hsi-bsp-voiture
Projet de Hardware Software Interface en Ing3 INEM

## Question 1 

We use a file `applicative_data.json` to specify the types and the initialisation values of the data that we want to use in the application. The file is structured as follows:

```json
{
    "types": [
        {
            "name": "example_atomic_type_t",
            "kind": "atomic",
            "declaration": "uint8_t",
            "domain": "",
            "comment": "This is an example of an atomic type"
        },
        {
            "name": "example_atomic_type_with_domain_t",
            "kind": "atomic",
            "declaration": "uint8_t",
            "domain": {
                "min": 0,
                "max": 255
            },
            "comment": "This is an example of an atomic type with a domain"
        },
        {
            "name": "example_flags_type_t",
            "kind": "flags",
            "declaration": {
                "type": "uint16_t",
                "flags": [
                    {
                        "name": "example_flag_1",
                        "bit_size": 1
                    },
                    {
                        "name": "example_flag_2",
                        "bit_size": 2
                    },
                    ...
                ]
            },
            "domain": "",
            "comment": "This is an example of a flag type"
        },
        {
            "name": "example_enum_type_t",
            "kind": "enum",
            "declaration": {
                "value_type": "uint8_t",
                "values": [
                    {
                        "name": "EXAMPLE_VALUE_1",
                        "value": 0
                    },
                    {
                        "name": "EXAMPLE_VALUE_2",
                        "value": 1
                    }
                ]
            },
            "domain": "",
            "comment": "This is an example of an enum type"
        },
        {
            "name": "example_struct_type_t",
            "kind": "struct",
            "declaration": [
                {
                    "name": "example_atomic_type_name_1",
                    "type": "example_atomic_type_1"
                },
                {
                    "name": "example_atomic_type_name_2",
                    "type": "example_atomic_type_2"
                }
            ],
            "domain": "",
            "comment": "This is an example of a struct type"
        }
    ],
    "data": [
        {
            "id": 1,
            "name": "example_struct",
            "kind": "init",
            "type": "example_struct_t",
            "dimension": 1,
            "initialization_value": [
                {
                    "name": "kilometer",
                    "value": 0
                },
                {
                    "name": "rpm",
                    "value": 0
                }
            ],
            "comment": "This is an example of an initialisation value"
        },
        {
            "id": 2,
            "name": "EXAMPLE_DEFINE",
            "kind": "define",
            "type": "",
            "dimension": 1,
            "initialization_value": 0,
            "comment": ""
        }
    ]
}
```

## Question 2

We create a tool in Rust that generates a static library that contains the types and the functions to manipulate these types. The tool reads the `applicative_data.json` file and generates the following files:

* `libs/data_lib/data_management.h` : Contains the declarations of the types and the functions to manipulate these types
* `libs/data_lib/data_management.c` : Contains the definitions of the functions to manipulate the types'

How to use the tool:

```bash
    ./tools/data_lib_generator/target/release/data_lib_generator [options]
```

### Options

* --json : Path to the json file; by default, it is set to `applicative_data.json`
* --dest : Path to the destination folder; by default, it is set to `libs/data_lib`


### Example

```bash
    ./tools/data_lib_generator/target/debug/data_lib_generator --json applicative_data.json --dest libs/data_lib
```

## Question 3
We initialise the file descriptor for the driver at the start of the program.
Then we use it to retrieve information via the UDP channel.

## Question 4
We decided to create three files to represent the different state machines.
The states and events are types that we created in the JSON file with all the data.
Each of the state machines returns the next state according to the previous state in order to assign it to a variable and continue the process.

## Question 5
We have a Makefile (Makefile.app) that compiles the application and another Makefile to compile the library.
These two Makefiles are combined in a single main Makefile.
The bash file (launch.sh) launches the driver and then the application.

## Question 6
The ‘decode.c’ file contains all our functions for decoding the raw information from the UDP and Serial outputs.
We transform the comodo frame into a specific type and the MUX frame into a type suitable for the BGCV.

## Question 7
The ‘encode.c’ file contains all our functions for encoding the transformed information to the UDP and Serial inputs.
We transform the custom frames into the original frames so that they match the data format expected by the driver.
We have encountered difficulties in synchronizing the data sent to the bgf with the data received for the acknowledgment.

## Question 8
We have structured our ‘main’ function in the ‘app.c’ file according to the tree structure expected by the specifications.
We also check the UDP frame number abd print to the terminal if there is an error.
