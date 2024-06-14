using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Guit_API.Data;
using Guit_API.Models;

namespace Guit_API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CommitsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CommitsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // Obtener un commit por ID
        [HttpGet("{id}")]
        public async Task<ActionResult<Commits>> GetCommit(int id)
        {
            var commit = await _context.Commits.FindAsync(id);

            if (commit == null)
            {
                return NotFound();
            }

            return commit;
        }

        // Crear un nuevo commit
        [HttpPost]
        public async Task<ActionResult<Commits>> PostCommit(Commits commit)
        {
            _context.Commits.Add(commit);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetCommit), new { id = commit.Id }, commit);
        }
    }
}
