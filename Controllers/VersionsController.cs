using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Guit_API.Data;
using Guit_API.Models;

namespace Guit_API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class VersionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public VersionsController(ApplicationDbContext context)
        {
            _context = context;
        }
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Versions>>> GetRepositorios()
        {
            return await _context.Versions.ToListAsync();
        }

        // Obtener una versión por ID
        [HttpGet("{id}")]
        public async Task<ActionResult<Versions>> GetVersion(int id)
        {
            var version = await _context.Versions.FindAsync(id);

            if (version == null)
            {
                return NotFound();
            }

            return version;
        }

        // Crear una nueva versión
        [HttpPost]
        public async Task<ActionResult<Versions>> PostVersion(Versions version)
        {
            _context.Versions.Add(version);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetVersion), new { id = version.id }, version);
        }
    }
}
