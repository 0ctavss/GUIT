using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Guit_API.Data;
using Guit_API.Models;

namespace Guit_API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class FileController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public FileController(ApplicationDbContext context)
        {
            _context = context;
        }
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Files>>> GetFiles()
        {
            return await _context.Files.ToListAsync();
        }
        // Obtener un archivo por ID
        [HttpGet("{id}")]
        public async Task<ActionResult<Files>> GetFile(int id)
        {
            var file = await _context.Files.FindAsync(id);

            if (file == null)
            {
                return NotFound();
            }

            return file;
        }

        // Crear un nuevo archivo
        [HttpPost]
        public async Task<ActionResult<Files>> PostFile(Files file)
        {
            _context.Files.Add(file);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetFile), new { id = file.id }, file);
        }
    }
}
