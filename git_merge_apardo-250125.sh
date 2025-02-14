#!/bin/bash

# Check if we are inside a Git repository
if [ ! -d .git ]; then
    echo "Error: Not a Git repository."
    exit 1
fi

# Get the current branch name
current_branch=$(git rev-parse --abbrev-ref HEAD)

# Check if the current branch is 'apardo-250125'
if [ "$current_branch" == "apardo-250125" ]; then
    echo "You are already on the 'apardo-250125' branch. Cannot merge with itself."
    exit 1
fi

# Check if the 'apardo-250125' branch exists
if ! git show-ref --verify --quiet refs/heads/apardo-250125; then
    echo "Error: The 'apardo-250125' branch does not exist."
    exit 1
fi

echo "Merging branch '$current_branch' with 'apardo-250125'..."

# Perform the merge with 'apardo-250125'
git merge apardo-250125

# Check if there were conflicts
if [ $? -ne 0 ]; then
    echo "⚠️  Merge conflicts detected. Resolve them and commit manually."
    exit 1
fi

echo "✅ Merge completed successfully."

