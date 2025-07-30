import json
import argparse
from jsonschema import validate, ValidationError
from jsonschema.validators import validator_for

def validate_json(json_data, schema_data):
    """
    Validate JSON data against a JSON Schema.
    
    Args:
        json_data (dict/str): JSON data to validate (as dict or JSON string)
        schema_data (dict/str): JSON Schema to validate against (as dict or JSON string)
    
    Returns:
        tuple: (bool, str) - (True, "") if valid, (False, error_message) if invalid
    """
    try:
        # Parse if inputs are strings
        if isinstance(json_data, str):
            json_data = json.loads(json_data)
        if isinstance(schema_data, str):
            schema_data = json.loads(schema_data)

        # Get the appropriate validator for the schema's version
        validator_class = validator_for(schema_data)
        validator = validator_class(schema_data)

        # Validate
        validator.validate(json_data)
        return True, "JSON is valid against the schema."

    except json.JSONDecodeError as e:
        return False, f"Invalid JSON: {str(e)}"
    except ValidationError as e:
        error_path = "->".join(str(item) for item in e.absolute_path)
        error_msg = f"Validation error at {error_path}: {e.message}"
        return False, error_msg
    except Exception as e:
        return False, f"Unexpected error: {str(e)}"

def load_json_file(file_path):
    """Load and parse a JSON file."""
    with open(file_path, 'r') as f:
        return json.load(f)

def main():
    # Set up command line argument parser
    parser = argparse.ArgumentParser(
        description='Validate JSON against a JSON Schema'
    )
    parser.add_argument(
        'json_file',
        help='Path to the JSON file to validate'
    )
    parser.add_argument(
        'schema_file',
        help='Path to the JSON Schema file'
    )
    parser.add_argument(
        '--verbose',
        '-v',
        action='store_true',
        help='Show detailed validation output'
    )

    args = parser.parse_args()

    try:
        # Load the files
        schema = load_json_file(args.schema_file)
        json_data = load_json_file(args.json_file)

        # Validate
        is_valid, message = validate_json(json_data, schema)

        # Output results
        if is_valid:
            print("✅ Validation successful!")
            if args.verbose:
                print(message)
        else:
            print("❌ Validation failed!")
            print(message)

        exit(0 if is_valid else 1)

    except FileNotFoundError as e:
        print(f"Error: File not found - {str(e)}")
        exit(1)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON - {str(e)}")
        exit(1)
    except Exception as e:
        print(f"Unexpected error: {str(e)}")
        exit(1)

if __name__ == "__main__":
    main()