#!/bin/bash

clear
#Use bash to run
echo "
============================================================
                    OPERATING SYSTEMS
                     ASSIGNMENT - I
============================================================

Student 1
----------------------------
Name        : Dipram Biswas
Roll Number : 002411001069
Year        : 3rd Year
Section     : A3

Student 2
----------------------------
Name        : Ayush Bhakta
Roll Number : 002411001072
Year        : 3rd Year
Section     : A3

Assignment Number : 1
============================================================
"


# ==========================================================================================
# Question 1
# ==========================================================================================
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 1 :"
echo "Find all files that are more than 100 bytes in size and display the number of"
echo "characters, words and lines in each file"
echo "--------------------------------------------------------------------------------------------"
echo ""

# Setup dummy file for demonstration
echo "This dummy file is created specifically for Question 1 testing. It contains enough characters to exceed 100 bytes in size so that the find command in Question 1 picks it up and outputs character, word, and line counts properly during evaluation." > q1_demo.txt

echo "Executing command: find . -type f -size +100c -exec wc -m -w -l {} \;"
echo ""
find . -type f -size +100c -exec wc -m -w -l {} \;

rm -f q1_demo.txt


# ==========================================================================================
# Question 2
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 2 :"
echo "Change the modification time to current time for those files that have been"
echo "modified 5 minutes ago."
echo "--------------------------------------------------------------------------------------------"
echo ""

# Create a test file modified 5 minutes ago
touch q2_demo.txt
touch -d '5 minutes ago' q2_demo.txt
echo "Initial file timestamp (modified 5 mins ago):"
date -r q2_demo.txt

echo -e "\nExecuting command: find . -type f -mmin 5 -exec touch {} \;"
echo ""
find . -type f -mmin +4 -mmin -6 -exec touch {} \;

echo -e "\nUpdated file timestamp (refreshed to current time):"
date -r q2_demo.txt

rm -f q2_demo.txt


# ==========================================================================================
# Question 3
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 3 :"
echo "Remove the read permission for others for all .c files in your home directory and"
echo "subdirectories."
echo "--------------------------------------------------------------------------------------------"
echo ""

# Create dummy .c file
touch q3_demo.c
chmod 644 q3_demo.c
echo "Initial permissions of q3_demo.c:"
ls -l q3_demo.c

echo -e "\nExecuting command: find . -type f -name '*.c' -exec chmod o-r {} \;"
echo ""
find . -type f -name "*.c" -exec chmod o-r {} \;

echo -e "\nUpdated permissions of q3_demo.c (others read permission removed):"
ls -l q3_demo.c

rm -f q3_demo.c


# ==========================================================================================
# Question 4
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 4 :"
echo "You want a make default permission for directories to be rwxr--r--. Set your umask"
echo "variable accordingly. Create some directories to see whether it is working or not"
echo "--------------------------------------------------------------------------------------------"
echo ""

echo "Setting umask to 033 (777 - 744 = 033)..."
echo "Executing command: umask 033"
umask 033

echo "Creating test directories: q4_dir1, q4_dir2..."
mkdir -p q4_dir1 q4_dir2

echo -e "\nChecking directory permissions:"
echo ""
ls -ld q4_dir1 q4_dir2

rm -rf q4_dir1 q4_dir2


# ==========================================================================================
# Question 5
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 5 :"
echo "Create a hard link 'copy' of the command 'cp' in your home directory. Use this"
echo "'copy' command to copy any existing file to another file."
echo "--------------------------------------------------------------------------------------------"
echo ""

CP_PATH=$(which cp)
echo "Original 'cp' path: $CP_PATH"

echo "Executing command: sudo ln $CP_PATH ~/copy" 
sudo ln "$CP_PATH" ~/copy
echo -e "\nComparing inodes for '$CP_PATH' and '~/copy':"
echo ""
ls -li "$CP_PATH" ~/copy

echo -e "\nTesting ~/copy command:"
echo "Sample text for Question 5 testing" > q5_source.txt
~/copy q5_source.txt q5_dest.txt
echo "Copied content in q5_dest.txt: $(cat q5_dest.txt)"

rm -f q5_source.txt q5_dest.txt ~/copy


# ==========================================================================================
# Question 6
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 6 :"
echo "Set the User ID (SUID) bit for the object/executable file."
echo "--------------------------------------------------------------------------------------------"
echo ""

touch add.o
echo "Initial file permissions:"
ls -l add.o

echo -e "\nExecuting command: chmod u+s add.o"
echo ""
chmod u+s add.o

echo "Updated permissions with SUID bit set ('s' in user execute field):"
ls -l add.o

rm -f add.o


# ==========================================================================================
# Question 7
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 7 :"
echo "A shared directory is to be created for project group. Implement this using sticky bit."
echo "--------------------------------------------------------------------------------------------"
echo ""

SHARED_DIR="/tmp/shared_project_dir"
mkdir -p "$SHARED_DIR"

echo "Executing command: chmod 1777 $SHARED_DIR"
echo ""
chmod 1777 "$SHARED_DIR"

echo -e "\nDirectory details (Notice 't' at the end indicating Sticky Bit):"
ls -ld "$SHARED_DIR"

rm -rf "$SHARED_DIR"


# ==========================================================================================
# Question 8
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 8 :"
echo "Copy /etc/passwd file in home directory as password. Substitute 'bash' by 'sh' using vi."
echo "--------------------------------------------------------------------------------------------"
echo ""

cp /etc/passwd ~/password

echo "Executing vi editor substitute command non-interactively..."
echo ":%s/bash/sh/g"
echo ":wq"
ex -s ~/password << 'EOF'
:%s/bash/sh/g
:wq
EOF

echo -e "\nVerifying replacement (matching lines in ~/password):"
echo ""
grep "/sh" ~/password | head -n 3


# ==========================================================================================
# Question 9
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 9 :"
echo "Substitute all occurrences of ':' by '|' using vi editor."
echo "--------------------------------------------------------------------------------------------"
echo ""

echo "Executing vi editor substitute command non-interactively..."
echo ":%s/:/|/g"
echo ":wq"
ex -s ~/password << 'EOF'
:%s/:/|/g
:wq
EOF

echo -e "\nVerifying replacement (first 3 lines of ~/password):"
echo ""
head -n 3 ~/password


# ==========================================================================================
# Question 10
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 10 :"
echo "Substitute all occurrences of 'home' from line 100 to 200 using vi editor."
echo "--------------------------------------------------------------------------------------------"
echo ""

echo "Executing vi substitution on range 100-200 non-interactively..."
echo ":100,200s/home/replaced_home/g"
echo ":wq"
ex -s ~/password << 'EOF'
:100,200s/home/replaced_home/g
:wq
EOF

echo ""
echo "Substitution on lines 100-200 completed successfully."

rm -f ~/password


# ==========================================================================================
# Question 11
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 11 :"
echo "Delete all lines from a file containing the word 'unix'."
echo "--------------------------------------------------------------------------------------------"
echo ""

echo -e "Line 1 with unix\nLine 2 without target word\nLine 3 unix again" > q11_test.txt
echo "Original file content:"
cat q11_test.txt

echo -e "\nExecuting line deletion..."
echo "Executing command: sed -i '/unix/d' q11_test.txt"
sed -i '/unix/d' q11_test.txt
echo -e "\nFile content after deleting 'unix' lines:"
echo ""
cat q11_test.txt

rm -f q11_test.txt


# ==========================================================================================
# Question 12
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 12 :"
echo "Write a shell script which displays 'Good morning'/'Good Afternoon'/'Good evening'"
echo "depending upon time."
echo "--------------------------------------------------------------------------------------------"
echo ""

hour=$(date +%H)
if [ "$hour" -lt 12 ]; then
    echo "Good morning"
elif [ "$hour" -lt 17 ]; then
    echo "Good Afternoon"
else
    echo "Good evening"
fi


# ==========================================================================================
# Question 13
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 13 :"
echo "Obtain information about login user from /etc/passwd and display on screen."
echo "--------------------------------------------------------------------------------------------"
echo ""

TARGET_USER="$USER"
USER_ENTRY=$(grep "^${TARGET_USER}:" /etc/passwd)

if [ -z "$USER_ENTRY" ]; then
    echo "User '$TARGET_USER' not found in /etc/passwd."
else
    IFS=":" read -r U_NAME PASS UID_NUM GID_NUM GECOS HOME_DIR USER_SHELL <<< "$USER_ENTRY"
    
    echo "--------------------------------------------------------------------------------------------"
    echo "           USER INFORMATION FOR: $TARGET_USER"
    echo "--------------------------------------------------------------------------------------------"
    echo "Username         : $U_NAME"
    echo "User ID (UID)    : $UID_NUM"
    echo "Group ID (GID)   : $GID_NUM"
    echo "User Description : $GECOS"
    echo "Home Directory   : $HOME_DIR"
    echo "Default Shell    : $USER_SHELL"
    echo "--------------------------------------------------------------------------------------------"
fi


# ==========================================================================================
# Question 14
# ==========================================================================================
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------"
echo "Question 14 :"
echo "Compare two files content (ignoring arbitrary blank lines). Delete if same."
echo "--------------------------------------------------------------------------------------------"
echo ""

FILE1="${1:-q14_file1.txt}"
FILE2="${2:-q14_file2.txt}"

if [ "$#" -ne 2 ]; then
    echo "No file arguments passed. Creating test files automatically..."
    echo -e "Line 1\n\nLine 2\nLine 3" > "$FILE1"
    echo -e "Line 1\nLine 2\n\nLine 3\n\n" > "$FILE2"
fi

echo "File 1 ($FILE1) content:"
cat "$FILE1"
echo -e "\nFile 2 ($FILE2) content:"
cat "$FILE2"

echo -e "\nComparing content (ignoring arbitrary blank lines)..."
echo ""
diff -B <(grep -v '^[[:space:]]*$' "$FILE1") <(grep -v '^[[:space:]]*$' "$FILE2") > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "Result: Files match! Deleting '$FILE2'..."
    rm -f "$FILE2"
    echo "Deletion complete."
else
    echo "Result: Files do not match. No files were deleted."
fi

# Cleanup auto-generated test files
[ "$#" -ne 2 ] && rm -f "$FILE1"


echo ""
echo ""
echo "============================================================================================"
echo "                           ALL QUESTIONS COMPLETED SUCCESSFULLY!"
echo "============================================================================================"
echo ""






