import gitlog from "gitlog";
import fs from "fs/promises";

const options = {
  repo: import.meta.dirname,
  fields: ["subject", "authorDate"],
};

function isReleaseCommit(commit) {
  return commit.subject.startsWith("release:");
}

function formatCommit(commit) {
  return {
    title: commit.subject.replace("release:", ""),
    when: commit.authorDate,
  };
}

const commits = (await gitlog(options))
  .filter(isReleaseCommit)
  .map(formatCommit);

await fs.writeFile("src/data/releaseNotes.gen.json", JSON.stringify(commits));
