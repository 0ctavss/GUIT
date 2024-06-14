using Guit_API.Models;
using Microsoft.EntityFrameworkCore;

namespace Guit_API.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {

        }
        public DbSet<Repositories> Repositories { get; set; }
        public DbSet<Files> Files { get; set; }
        public DbSet<Commits> Commits { get; set; }
        public DbSet<Versions> Versions { get; set; }
        public DbSet<fileToCommit> files_to_commit { get; set; }
        public DbSet<IgnoreFiles> ignore_files { get; set; }

    }
}

