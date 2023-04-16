import os
import re
import sys
from github import Github

def main():
    token = os.environ["GITHUB_PAT"]
    gist_id = "YOUR_GIST_ID"

    github = Github(token)
    repo = github.get_repo(os.environ["GITHUB_REPOSITORY"])
    gist = github.get_gist(gist_id)

    issue_number = int(os.environ["ISSUE_NUMBER"])
    issue = repo.get_issue(issue_number)

    points = 0

    for label in issue.labels:
        if label.name.startswith("puntos:"):
            points = float(re.findall(r"\d+\.\d+", label.name)[0])
            break

    if points > 0:
        content = gist.files["puntaje"].content
        current_score = float(content.strip())
        new_score = current_score + points
        gist.edit(files={ "puntaje": { "content": str(new_score) } })

if __name__ == "__main__":
    main()
