#!/bin/bash

# Test script for cub3D validation
# This tests all validation requirements without running the game

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "======================================"
echo "    CUB3D VALIDATION TEST SUITE"
echo "======================================"
echo ""

# Compile the test program
echo -e "${YELLOW}Compiling test program...${NC}"
make -f Makefile.standalone
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation successful!${NC}"
echo ""

# Create test directory
mkdir -p test_maps

# Function to run test
run_test() {
    local test_name=$1
    local test_file=$2
    local expected_result=$3
    
    ./test_standalone "$test_file" > /dev/null 2>&1
    local result=$?
    
    if [ $expected_result -eq 0 ]; then
        # Should pass
        if [ $result -eq 0 ]; then
            echo -e "${GREEN}✓${NC} $test_name"
        else
            echo -e "${RED}✗${NC} $test_name (Expected pass, got fail)"
        fi
    else
        # Should fail
        if [ $result -ne 0 ]; then
            echo -e "${GREEN}✓${NC} $test_name"
        else
            echo -e "${RED}✗${NC} $test_name (Expected fail, got pass)"
        fi
    fi
}

echo "======================================"
echo "1. ARGUMENT VALIDATION TESTS"
echo "======================================"

# Test 1: No arguments
echo -e "${YELLOW}Testing no arguments...${NC}"
./test_standalone 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓${NC} No arguments correctly rejected"
else
    echo -e "${RED}✗${NC} No arguments should fail"
fi

# Test 2: Too many arguments
echo -e "${YELLOW}Testing too many arguments...${NC}"
./test_standalone file1.cub file2.cub 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓${NC} Too many arguments correctly rejected"
else
    echo -e "${RED}✗${NC} Too many arguments should fail"
fi

# Test 3: Wrong extension
echo -e "${YELLOW}Testing wrong extension...${NC}"
echo "test" > test_maps/wrong.txt
./test_standalone test_maps/wrong.txt 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓${NC} Wrong extension correctly rejected"
else
    echo -e "${RED}✗${NC} Wrong extension should fail"
fi

# Test 4: Non-existent file
echo -e "${YELLOW}Testing non-existent file...${NC}"
./test_standalone nonexistent.cub 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓${NC} Non-existent file correctly rejected"
else
    echo -e "${RED}✗${NC} Non-existent file should fail"
fi

echo ""
echo "======================================"
echo "2. PARAMETER VALIDATION TESTS"
echo "======================================"

# Test 5: Missing parameters
cat > test_maps/missing_params.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0

111111
100001
1N0001
100001
111111
EOF
run_test "Missing ceiling color" "test_maps/missing_params.cub" 1

# Test 6: Duplicate parameters
cat > test_maps/duplicate_params.cub << EOF
NO ./north.xpm
NO ./north2.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

111111
100001
1N0001
100001
111111
EOF
run_test "Duplicate texture parameter" "test_maps/duplicate_params.cub" 1

# Test 7: Invalid RGB format
cat > test_maps/invalid_rgb.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100
C 225,30,0

111111
100001
1N0001
100001
111111
EOF
run_test "Invalid RGB format (missing value)" "test_maps/invalid_rgb.cub" 1

# Test 8: RGB out of range
cat > test_maps/rgb_out_of_range.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 256,100,0
C 225,30,0

111111
100001
1N0001
100001
111111
EOF
run_test "RGB value out of range" "test_maps/rgb_out_of_range.cub" 1

# Test 9: Non-numeric RGB
cat > test_maps/non_numeric_rgb.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,abc,0
C 225,30,0

111111
100001
1N0001
100001
111111
EOF
run_test "Non-numeric RGB value" "test_maps/non_numeric_rgb.cub" 1

echo ""
echo "======================================"
echo "3. MAP VALIDATION TESTS"
echo "======================================"

# Test 10: Invalid character in map
cat > test_maps/invalid_char.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

111111
100001
1N0X01
100001
111111
EOF
run_test "Invalid character in map" "test_maps/invalid_char.cub" 1

# Test 11: No player
cat > test_maps/no_player.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

111111
100001
100001
100001
111111
EOF
run_test "No player in map" "test_maps/no_player.cub" 1

# Test 12: Multiple players
cat > test_maps/multiple_players.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

111111
1N0001
100S01
100001
111111
EOF
run_test "Multiple players in map" "test_maps/multiple_players.cub" 1

# Test 13: Map not enclosed (hole in wall)
cat > test_maps/not_enclosed.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

111111
100001
1N0000
100001
111111
EOF
run_test "Map not enclosed" "test_maps/not_enclosed.cub" 1

# Test 14: Content after map
cat > test_maps/content_after_map.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

111111
100001
1N0001
100001
111111

Extra content
EOF
run_test "Content after map" "test_maps/content_after_map.cub" 1

# Test 15: Valid map with spaces
cat > test_maps/valid_with_spaces.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

    111111
    100001
    1N0001
    100001
    111111
EOF
run_test "Valid map with spaces" "test_maps/valid_with_spaces.cub" 0

# Test 16: Valid complete map
cat > test_maps/valid_complete.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

11111111111111
10000000000001
10000000000001
10000N00000001
10000000000001
10000000000001
11111111111111
EOF
run_test "Valid complete map" "test_maps/valid_complete.cub" 0

echo ""
echo "======================================"
echo "4. EDGE CASES"
echo "======================================"

# Test 17: Empty file
touch test_maps/empty.cub
run_test "Empty file" "test_maps/empty.cub" 1

# Test 18: Only parameters, no map
cat > test_maps/no_map.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0
EOF
run_test "Only parameters, no map" "test_maps/no_map.cub" 1

# Test 19: Map with irregular shape (valid)
cat > test_maps/irregular_valid.cub << EOF
NO ./north.xpm
SO ./south.xpm
WE ./west.xpm
EA ./east.xpm
F 220,100,0
C 225,30,0

  1111111
  1000001
  10N0001
111000001
100000001
100000111
1111111
EOF
run_test "Irregular but valid map" "test_maps/irregular_valid.cub" 0

echo ""
echo "======================================"
echo "        TEST SUITE COMPLETE"
echo "======================================"

# Clean up
rm -rf test_maps
rm -f test_standalone

echo ""
echo "Note: This tests validation only. Game rendering is not tested."
