use std::io;

fn main() -> io::Result<()> {
    println!("What's your name?");
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer)?;
    println!("Hello, {}", buffer);
    Ok(())
}
