#!/bin/bash

# Check if we are inside a Git repository
if [ ! -d .git ]; then
    echo "Error: Not a Git repository."
    exit 1
fi

# Get the current branch name
current_branch=$(git rev-parse --abbrev-ref HEAD)

# Check if the current branch is 'castorga'
if [ "$current_branch" == "castorga" ]; then
    echo "You are already on the 'castorga' branch. Cannot merge with itself."
    exit 1
fi

# Check if the 'castorga' branch exists
if ! git show-ref --verify --quiet refs/heads/castorga; then
    echo "Error: The 'castorga' branch does not exist."
    exit 1
fi

echo "Merging branch '$current_branch' with 'castorga'..."

# Perform the merge with 'castorga'
git merge castorga

# Check if there were conflicts
if [ $? -ne 0 ]; then
    echo "⚠️  Merge conflicts detected. Resolve them and commit manually."
    exit 1
fi

echo "✅ Merge completed successfully."

