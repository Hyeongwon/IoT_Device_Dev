package edu.mds.vo;

public class Product {
	
	private int pcdoe;
	private String pname;
	private int price;
	private int quant;
	private String pdesc = "";

	public int getPcdoe() {
		return pcdoe;
	}

	public void setPcdoe(int pcdoe) {
		this.pcdoe = pcdoe;
	}

	public String getPname() {
		return pname;
	}

	public void setPname(String pname) {
		this.pname = pname;
	}

	public int getPrice() {
		return price;
	}

	public void setPrice(int price) {
		this.price = price;
	}

	public int getQuant() {
		return quant;
	}

	public void setQuant(int quant) {
		this.quant = quant;
	}

	public String getPdesc() {
		return pdesc;
	}

	public void setPdesc(String pdesc) {
		this.pdesc = pdesc;
	}

	public Product(int pcdoe, String pname, int price, int quant, String pdesc) {
		super();
		this.pcdoe = pcdoe;
		this.pname = pname;
		this.price = price;
		this.quant = quant;
		this.pdesc = pdesc;
	}

	public Product() {
		super();
	}

	@Override
	public String toString() {
		return "Product [pcdoe=" + pcdoe + ", pname=" + pname + ", price=" + 
							price + ", quant=" + quant + ", pdesc=" + pdesc + "]";
	}

	

}
