#!/bin/bash

# Check if we are inside a Git repository
if [ ! -d .git ]; then
    echo "Error: Not a Git repository."
    exit 1
fi

# Get the current branch name
current_branch=$(git rev-parse --abbrev-ref HEAD)

# Check if the current branch is 'lin'
if [ "$current_branch" == "lin" ]; then
    echo "You are already on the 'lin' branch. Cannot merge with itself."
    exit 1
fi

# Check if the 'lin' branch exists
if ! git show-ref --verify --quiet refs/heads/lin; then
    echo "Error: The 'lin' branch does not exist."
    exit 1
fi

echo "Merging branch '$current_branch' with 'lin'..."

# Perform the merge with 'lin'
git merge lin

# Check if there were conflicts
if [ $? -ne 0 ]; then
    echo "⚠️  Merge conflicts detected. Resolve them and commit manually."
    exit 1
fi

echo "✅ Merge completed successfully."

