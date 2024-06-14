namespace Guit_API.Models
{
    public class Repositories
    {
        public int id { get; set; }
        public required string name { get; set; }
        public DateTime created_at { get; set; }
    }
    public class Files
    {
        public int id { get; set; }
        public int repository_id { get; set; }
        public required string file_path { get; set; }
        public required string content { get; set; }
        public DateTime created_at { get; set; }


    }
    public class Commits
    {
        public int id { get; set; }
        public int repository_id { get; set; }

        public int commit_hash { get; set; }
        public required string message { get; set; }
        public DateTime created_at { get; set; }
        public required string checksum { get; set; }
    }
    public class Versions
    {
        public int id { get; set; }
        public int file_id { get; set; }
        public int commit_id { get; set; }

        public required string delta { get; set; }
        public DateTime created_at { get; set; }
    }
    public class fileToCommit
    {
        public int id { get; set; }
        public int file_id { get; set; }
        public int commit_id { get; set; }
    }
    public class IgnoreFiles
    {
        public int id { get; set; }
        public int repository_id { get; set; }
        public required char pattern { get; set; }
    }

}
