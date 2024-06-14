
using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using global::Guit_API.Data;
using global::Guit_API.Models;

namespace Guit_API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class IgnoreFilesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public IgnoreFilesController(ApplicationDbContext context)
        {
            _context = context;
        }
        [HttpGet]
        public async Task<ActionResult<IEnumerable<IgnoreFiles>>> GetRepositorios()
        {
            return await _context.ignore_files.ToListAsync();
        }
        // Obtener un archivo ignorado por ID
        [HttpGet("{id}")]
        public async Task<ActionResult<IgnoreFiles>> GetIgnoreFile(int id)
        {
            var ignoreFile = await _context.ignore_files.FindAsync(id);

            if (ignoreFile == null)
            {
                return NotFound();
            }

            return ignoreFile;
        }

        // Crear un nuevo archivo ignorado
        [HttpPost]
        public async Task<ActionResult<IgnoreFiles>> PostIgnoreFile(IgnoreFiles ignoreFile)
        {
            _context.ignore_files.Add(ignoreFile);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetIgnoreFile), new { id = ignoreFile.id }, ignoreFile);
        }
    }
}
