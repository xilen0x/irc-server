#!/bin/bash

# Check if we are inside a Git repository
if [ ! -d .git ]; then
    echo "❌ Error: Not a Git repository."
    exit 1
fi

# Get the current branch name
current_branch=$(git rev-parse --abbrev-ref HEAD)

# Check if the current branch is 'apardo-250125'
if [ "$current_branch" == "apardo-250125" ]; then
    echo "❌ You are already on the 'apardo-250125' branch. Cannot merge with itself."
    exit 1
fi

# Check if the 'apardo-250125' branch exists
if ! git show-ref --verify --quiet refs/heads/apardo-250125; then
    echo "❌ Error: The 'apardo-250125' branch does not exist."
    exit 1
fi

# Switch to the target branch to pull the latest changes
echo "🔄 Switching to 'apardo-250125' and pulling latest changes..."
git checkout apardo-250125

if [ $? -ne 0 ]; then
    echo "❌ Error: Could not switch to 'apardo-250125'."
    exit 1
fi

git pull origin apardo-250125

if [ $? -ne 0 ]; then
    echo "❌ Error: Failed to pull the latest changes from 'apardo-250125'."
    exit 1
fi

# Switch back to the original branch
echo "🔄 Switching back to '$current_branch'..."
git checkout "$current_branch"

if [ $? -ne 0 ]; then
    echo "❌ Error: Could not switch back to '$current_branch'."
    exit 1
fi

echo "🔀 Merging 'apardo-250125' into '$current_branch'..."
git merge apardo-250125

# Check if there were conflicts
if [ $? -ne 0 ]; then
    echo "⚠️ Merge conflicts detected. Resolve them and commit manually."
    exit 1
fi

echo "✅ Merge completed successfully."

