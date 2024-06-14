using Guit_API.Data;
using Guit_API.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace Guit_API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class RepositoriesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public RepositoriesController(ApplicationDbContext context)
        {
            _context = context;
        }
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Repositories>>> GetRepositorios()
        {
            return await _context.Repositories.ToListAsync();
        }
        //GET: api/Repositories/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Repositories>> GetRepositorio(int id)
        {
            var repositorio = await _context.Repositories.FindAsync(id);

            if (repositorio == null)
            {
                return NotFound();
            }

            return repositorio;
        }
        // PUT: api/Repositories/5
        [HttpPost]
        public async Task<ActionResult<Repositories>> PostRepositorio(Repositories repositorio)
        {
            _context.Repositories.Add(repositorio);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetRepositorio), new { id = repositorio.id }, repositorio);
        }
        [HttpPut("{id}")]
        public async Task<IActionResult> PutRepositorio(int id, Repositories repositorio)
        {
            if (id != repositorio.id)
            {
                return BadRequest();
            }

            _context.Entry(repositorio).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!RepositoryExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }
        private bool RepositoryExists(int id)
        {
            return _context.Repositories.Any(e => e.id == id);
        }
    }
   
}
